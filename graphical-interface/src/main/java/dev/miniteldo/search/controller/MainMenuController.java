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
    private final ArrayList<String> positiveKeyword = new ArrayList<>();
    private final ArrayList<String> negativeKeyword = new ArrayList<>();

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

        if(searcherType == SearcherType.TEXT_KEYWORD) splitKeyword();

        searchResults = switch (searcherType) {
            case TEXT_PATH -> engine.textFileSearch(request);
            case TEXT_KEYWORD -> engine.keywordSearch(positiveKeyword, negativeKeyword);
            case IMAGE_RGB_PATH -> engine.rgbImageSearch(request);
            case IMAGE_NB_PATH -> engine.bwImageSearch(request);
            case AUDIO_PATH -> engine.audioSearch(request);
        };

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
        Pattern p = Pattern.compile("\\+\\w+|\\-\\w+|\\w+");
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
        return switch (regex) {
            case REGEX_TEXTE_KEYWORD -> SearcherType.TEXT_KEYWORD;
            case REGEX_TEXTE_PATH -> SearcherType.TEXT_PATH;
            case REGEX_IMAGE_NB -> SearcherType.IMAGE_NB_PATH;
            case REGEX_IMAGE_RGB -> SearcherType.IMAGE_RGB_PATH;
            case REGEX_AUDIO -> SearcherType.AUDIO_PATH;
            default -> null;
        };
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
