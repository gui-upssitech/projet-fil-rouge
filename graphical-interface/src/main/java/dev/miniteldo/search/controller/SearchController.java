package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.TextSearcher;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.model.tools.Regex;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.AudioPlayer;
import dev.miniteldo.search.view.ResultDisplayFactory;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.enums.Component;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.controlsfx.control.textfield.TextFields;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SearchController {

    /* Attibutes */

    @FXML
    public Button saveButton;
    @FXML
    public Button searchButton;
    @FXML
    public TextField requestLabel;
    @FXML
    public Button fileButton;
    @FXML
    public ColorPicker colorPicker;
    @FXML
    private VBox resultContainer, previewBox;

    private AppState state;
    private SearcherType requestType;
    private String request;
    private ArrayList<SearchResult> searchResults;

    /* FXML Methods */
    public void initialize() {
        state = AppState.getInstance();

        // Init get data from state
        request = state.getCurrentRequest().trim();
        requestLabel.setText(request);

        if (request.matches(Regex.REGEX_IMAGE_COLOR.getRegexExp())) {
            colorPicker.setValue(Color.web(request));
        }

        // Search logic
        requestType = Tools.getRequestType(request);

        // Do the search from request passed
        ArrayList<SearchResult> resultList = performSearch(fixRequestFormat(request));


        displayResults(resultList);

        // Add auto completion to the search bar
        TextSearcher textSearcher = (TextSearcher) SearcherFactory.getSearcher("search-engine", SearcherType.TEXT_COMPLETION);
        ArrayList<String> stringArrayList = new ArrayList<>();
        try {
            stringArrayList = textSearcher.getWordsList();
        } catch (IOException e) {
            e.printStackTrace();
        }
        TextFields.bindAutoCompletion(requestLabel, stringArrayList.toArray());
    }

    private void previewResult(SearchResult result) {
        Node preview = ResultDisplayFactory.createPreview(result);

        if(requestType == SearcherType.AUDIO_PATH) {
            AudioPlayer player = (AudioPlayer) previewBox.lookup("#audio-player");
            if(player != null) player.stop();
        }

        previewBox.getChildren().clear();
        previewBox.getChildren().add(preview);
    }

    @FXML
    protected void onReturnButton() {
        if (!AppState.getInstance().isPopUp()) {
            if(requestType == SearcherType.AUDIO_PATH) {
                AudioPlayer player = (AudioPlayer) previewBox.lookup("#audio-player");
                if(player != null) player.stop();
            }

            App.setView(Views.MAIN);
        }
    }

    @FXML
    protected void onSaveButton() {
        // Avoid multi pop up
        if (!AppState.getInstance().isPopUp()) {
            if (FileTools.saveRequest(request, searchResults)) {
                App.showDialog(Dialog.SUCCESS, "La requête a été sauvegardée");
            }
        }
    }

    /* Other methods */

    private ArrayList<SearchResult> performSearch(String request) {
        if (requestType == null) return null;

        SearchEngine engine = state.getEngine();

        // Expression cases
        if (requestType == SearcherType.TEXT_KEYWORD) {
            // Special case : keyword search
            ArrayList<String> positiveKeywords = getKeywords(request, true);
            ArrayList<String> negativeKeywords = getKeywords(request, false);
            searchResults = engine.keywordSearch(positiveKeywords, negativeKeywords);
        } else if (requestType == SearcherType.IMAGE_COLOR) {
            searchResults = engine.hexacodeImageSearch(request);
        } else {
            // Begin by checking if requested file exists
            File tempFile = new File(request);
            if (!tempFile.exists()) searchResults = null;
            else {
                // Perform corresponding search
                searchResults = switch (requestType) {
                    case TEXT_PATH -> engine.textFileSearch(request);
                    case IMAGE_RGB_PATH -> engine.rgbImageSearch(request);
                    case IMAGE_NB_PATH -> engine.bwImageSearch(request);
                    case AUDIO_PATH -> engine.audioSearch(request);
                    default -> null;
                };
            }
        }

        return searchResults;
    }

    public ArrayList<String> getKeywords(String request, boolean positive) {
        Matcher m = Pattern.compile("([+|-]?)(\\w+)").matcher(request);

        ArrayList<String> list = new ArrayList<>();
        while (m.find()) {
            boolean toAdd = m.group(1).equals("-") ^ positive; // [^ positive] inverts result if positive is true
            if (toAdd) list.add(m.group(2));
        }

        return list;
    }

    private void displayResults(ArrayList<SearchResult> liste) {
        if (liste == null || liste.isEmpty()) resultContainer.getChildren().add(new Label("Aucun résultat ..."));
        else {
            previewResult(liste.get(0));
            for (SearchResult searchResult : liste) {
                HBox result = SearchResultComponentFactory.createComponent(Component.SEARCH_RESULT, null, requestType, searchResult, event -> previewResult(searchResult));
                resultContainer.getChildren().add(result);
            }
        }
    }

    public void onSearchButton() {
        // get the new request
        if (!Tools.isRequestValid(request)) {
            App.showDialog(Dialog.ERROR, "Problème, requête invalide !");
        } else {
            // clear container
            resultContainer.getChildren().clear();

            request = requestLabel.getText();
            requestType = Tools.getRequestType(request);
            state.setCurrentRequest(request);

            // get research type

            // execute search
            ArrayList<SearchResult> resultList = performSearch(fixRequestFormat(requestLabel.getText()));

            displayResults(resultList);
        }
    }

    public void onEnterAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            onSearchButton();
        }
    }

    public void onEscapeAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE)) {
            onReturnButton();
        }
    }

    public void onFileButton(ActionEvent event) {
        Stage stage = (Stage) requestLabel.getScene().getWindow();
        File file = FileTools.getInputFile(stage);

        if (file != null) {
            requestLabel.setText(file.toString());
        }
    }

    private String fixRequestFormat(String req) {
        // Delete # character
        if (requestType == SearcherType.IMAGE_COLOR) {
            return req.substring(1);
        } else {
            return req;
        }
    }

    public void onColorAction(ActionEvent event) {
        String temp = "#" + colorPicker.getValue().toString().toUpperCase().substring(2, 8);
        requestLabel.setText(temp);
    }
}
