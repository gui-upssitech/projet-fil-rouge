package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.Regex;
import dev.miniteldo.search.model.tools.StringModifier;
import dev.miniteldo.search.view.Dialog;
import dev.miniteldo.search.view.Views;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class MainMenuController {
    public TextField searchBar;
    public Button searchButton;

    public String request;
    private ArrayList<String> positiveKeyword = new ArrayList<>();
    private ArrayList<String> negativeKeyword = new ArrayList<>();

    @FXML
    protected void onSearchButton(ActionEvent event) {
        // TODO ADD EXISTING AND CORRECT FILE CHECK
        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {
            // PopUpError modal window
            App.showDialog(Dialog.ERROR);

        } else {
            // Get the request Remove space
            request = StringModifier.removeAllSpace(searchBar.getText().trim());

            // Get Type of the request with regex
            SearcherType searcherTypeRequest = checkRegex(request);

            // Verification of the request
            if (searcherTypeRequest == null) {
                // PopUpError modal window
                App.showDialog(Dialog.ERROR);
            } else {
                // Call the C function
                executeRequest(searcherTypeRequest);

                App.setView(Views.SEARCH_RESULT);

            }

        }
    }

    public boolean executeRequest(SearcherType searcherType) {
        // Variable
        SearchEngine engine = AppState.getInstance().getEngine();
        ArrayList<SearchResult> searchResults = null;

        if (searcherType != SearcherType.TEXT_KEYWORD) {
            File tempFile = new File(request);
            if (!tempFile.exists()) {
                // PopUpError modal window
                App.showDialog(Dialog.ERROR);
                return false;
            }
        }

        switch (searcherType) {
            case TEXT_PATH:
                searchResults = engine.textFileSearch(request);
                break;
            case TEXT_KEYWORD:
                splitKeyword();
                searchResults = engine.keywordSearch(positiveKeyword, negativeKeyword);
                break;
            case IMAGE_RGB_PATH:
                searchResults = engine.rgbImageSearch(request);
                break;
            case IMAGE_NB_PATH:
                searchResults = engine.bwImageSearch(request);
                break;
            case AUDIO_PATH:
                searchResults = engine.audioSearch(request);
                break;
            default:
                searchResults = new ArrayList<>();
                break;
        }

        AppState.getInstance().setCurrentRequest(searchResults);

        System.out.println("Votre recherche : " + request);
        for (SearchResult result : searchResults) {
            System.out.println(result);
        }

        return true;
    }

    public SearcherType checkRegex(String request) {
        // Variable
        Pattern p;
        Matcher m;

        // Check each regex
        for (Regex regex : Regex.values()) {
            p = Pattern.compile(regex.getRegexExp());
            m = p.matcher(request);

            // If we found a match
            if (m.matches()) {
                return convertRegexToSearchType(regex);
            }
        }
        return null;
    }

    public void splitKeyword() {
        Pattern p = Pattern.compile(Regex.REGEX_TEXTE_KEYWORD.getRegexExp());
        Matcher m = p.matcher(request);

        String value = "";

        while (m.find()) {
            value = m.group();

            switch (m.group().charAt(0)) {
                case '-':
                    value = m.group().substring(1);
                    negativeKeyword.add(value);
                    break;
                case '+':
                    value = m.group().substring(1);
                default:
                    positiveKeyword.add(value);
                    break;
            }
        }
    }

    // FIXME: 17/03/2022 MOVE THIS TRASH FUNCTION
    public SearcherType convertRegexToSearchType(Regex regex) {
        switch (regex) {
            case REGEX_TEXTE_KEYWORD:
                return SearcherType.TEXT_KEYWORD;
            case REGEX_TEXTE_PATH:
                return SearcherType.TEXT_PATH;
            case REGEX_IMAGE_NB:
                return SearcherType.IMAGE_NB_PATH;
            case REGEX_IMAGE_RGB:
                return SearcherType.IMAGE_RGB_PATH;
            case REGEX_AUDIO:
                return SearcherType.AUDIO_PATH;
            default:
                return null;

        }
    }

    @FXML
    protected void onParamButton() {
        App.setView(Views.PARAMETERS);
    }

    @FXML
    protected void onFileButton() {
        Stage stage = (Stage) searchButton.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("All Files", "*.*"), new FileChooser.ExtensionFilter("JPG", "*.jpg"), new FileChooser.ExtensionFilter("PNG", "*.png"));

        // Set title for FileChooser
        fileChooser.setTitle("Select Some Files");

        // Set Initial Directory
        String currentPath = Paths.get("").toAbsolutePath().toString();
        fileChooser.setInitialDirectory(new File(currentPath));
        File file = fileChooser.showOpenDialog(stage);
        if (file != null) {
            searchBar.setText(file.toString());
        }
    }
}
