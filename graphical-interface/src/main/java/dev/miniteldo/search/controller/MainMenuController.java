package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.tools.Regex;
import dev.miniteldo.search.model.tools.StringModifier;
import dev.miniteldo.search.view.Dialog;
import dev.miniteldo.search.view.Error;
import dev.miniteldo.search.view.Views;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class MainMenuController {
    public TextField searchBar;
    public Button searchButton;

    public String requete;

    @FXML
    protected void onSearchButton(ActionEvent event) {
        // TODO ADD EXISTING AND CORRECT FILE CHECK
        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {

            // PopUpError modal window
            App.showDialog(Dialog.ERROR);

        } else {
            // Remove space
            requete = searchBar.getText().trim();
            System.out.println(StringModifier.removeAllSpace(requete));

            // TODO CHECK TYPE OF RESEARCH WITH A SWITCH ON COMBOBOX

            Pattern p = Pattern.compile(Regex.REGEX_TEXTE.getRegexExp());
            Matcher m = p.matcher(requete);
            // lancement de la recherche de toutes les occurrences
            System.out.println(m.matches());

            App.setView(Views.SEARCH_RESULT);
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
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("All Files", "*.*"),
                new FileChooser.ExtensionFilter("JPG", "*.jpg"),
                new FileChooser.ExtensionFilter("PNG", "*.png"));

        // Set title for FileChooser
        fileChooser.setTitle("Select Some Files");

        // Set Initial Directory
        fileChooser.setInitialDirectory(new File(System.getProperty("user.home")));
        File file = fileChooser.showOpenDialog(stage);
        System.out.println(file);
        if (file != null) {
            searchBar.setText(file.toString());
        }
    }
}
