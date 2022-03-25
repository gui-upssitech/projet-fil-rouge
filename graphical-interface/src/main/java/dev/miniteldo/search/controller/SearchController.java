package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.model.tools.Regex;
import dev.miniteldo.search.model.tools.StringModifier;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.Component;
import dev.miniteldo.search.view.Dialog;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

import java.io.File;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SearchController {

    /* Attibutes */

    @FXML
    public Button saveButton;
    @FXML
    public Button returnButton;
    public TextField requestLabel;

    @FXML
    private VBox resultContainer;

    private AppState state;
    private SearcherType requestType;
    private String request;
    private ArrayList<SearchResult> searchResults;

    /* FXML Methods */
    public void initialize() {
        state = AppState.getInstance();

        // Search logic
        request = state.getCurrentRequest();
        requestLabel.setText(request);

        requestType = Tools.getRequestType(request);
        ArrayList<SearchResult> resultList = performSearch(request);

        displayResults(resultList);
    }

    private void onResultClicked(SearchResult result) {
        System.out.println("Clicked result : " + result.getFilePath());
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }

    @FXML
    protected void onSaveButton() {
        if (FileTools.saveRequest(request, searchResults)) {
            App.showDialog(Dialog.SUCCESS);
            System.out.println("Save de la requête réussi !");
        }
    }

    /* Other methods */

    private ArrayList<SearchResult> performSearch(String request) {
        if (requestType == null) return null;


        SearchEngine engine = state.getEngine();

        if (requestType == SearcherType.TEXT_KEYWORD) {
            // Special case : keyword search
            ArrayList<String> positiveKeywords = getKeywords(request, true);
            ArrayList<String> negativeKeywords = getKeywords(request, false);
            searchResults = engine.keywordSearch(positiveKeywords, negativeKeywords);
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
        if (liste == null || liste.isEmpty())
            resultContainer.getChildren().add(new Label("No results found"));
        else {
            for (SearchResult searchResult : liste) {
                HBox result = SearchResultComponentFactory.createComponent(
                        Component.SEARCH_RESULT,
                        null,
                        requestType,
                        searchResult,
                        event -> onResultClicked(searchResult)
                );
                resultContainer.getChildren().add(result);
            }
        }
    }
}
