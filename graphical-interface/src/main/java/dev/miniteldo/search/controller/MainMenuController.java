package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.SearchResult;
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
            Regex resultRegex = checkRegex(request);

            // Verification of the request
            if (resultRegex.equals(Regex.INVALID)) {
                // PopUpError modal window
                App.showDialog(Dialog.ERROR);
            } else {
                if (!resultRegex.equals(Regex.REGEX_TEXTE_KEYWORD)) {
                    File tempFile = new File(request);
                    if (tempFile.exists()) {
                        // PopUpError modal window
                        App.showDialog(Dialog.ERROR);
                    } else {
                        // FIXME: 17/03/2022 add the method to load the path research
                    }
                } else {
                    // FIXME: 17/03/2022 add the keyword research
                }

                SearchEngine engine = AppState.getInstance().getEngine();
                System.out.println("Votre recherche : " + request);
                ArrayList<SearchResult> searchResults = engine.textFileSearch(request);

                for (SearchResult result : searchResults) {
                    System.out.println(result);
                }

                App.setView(Views.SEARCH_RESULT);
            }

        }
    }

    public Regex checkRegex(String request) {
        // Variable
        Pattern p;
        Matcher m;

        // Check each regex
        for (Regex regex : Regex.values()) {
            p = Pattern.compile(regex.getRegexExp());
            m = p.matcher(request);

            // If we found a match
            if (m.matches()) {
                return regex;
            }
        }
        return Regex.INVALID;
    }

    @FXML
    protected void onParamButton() {
        App.setView(Views.PARAMETERS);
    }

    @FXML
    protected void onFileButton() {
        Stage stage = (Stage) searchButton.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("All Files", "*.*"),
                new FileChooser.ExtensionFilter("JPG", "*.jpg"),
                new FileChooser.ExtensionFilter("PNG", "*.png"));

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
