package com.miniteldo;

import com.miniteldo.tools.Regex;
import com.miniteldo.tools.StringModifier;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.util.Objects;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class MainMenuController {
    public TextField searchBar;
    public Button searchButton;
    public Label messError;

    public String requete;
    public Button fileButton;
    public Button paramButton;

    @FXML
    protected void onSearchButton() throws IOException {
        // TODO ADD EXISTING AND CORRECT FILE CHECK
        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {
            messError.setText("Erreur, votre requête est vide");
        } else {
            // Remove space
            requete = searchBar.getText().trim();
            System.out.println(StringModifier.removeAllSpace(requete));

            // TODO CHECK TYPE OF RESEARCH WITH A SWITCH ON COMBOBOX
            messError.setText("Votre requête contient : \"" + searchBar.getText() + "\"");

            Pattern p = Pattern.compile(Regex.REGEX_TEXTE.getRegexExp());
            Matcher m = p.matcher(requete);
            // lancement de la recherche de toutes les occurrences
            System.out.println(m.matches());


//            // Close the current page
//            Stage stage = (Stage) searchBar.getScene().getWindow();
//            stage.close();
//
//            // load a new page
//            Stage nextpage = new Stage();
//            Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("result-search.fxml")));
//            Scene scene = new Scene(root);
//            nextpage.setTitle("Résultat recherche");
//            nextpage.setScene(scene);
//            nextpage.show();
        }
    }

    @FXML
    protected void onParamButton() throws IOException {
        // Close the current page
        Stage stage = (Stage) searchButton.getScene().getWindow();
        stage.close();

        Stage nextpage = new Stage();
        Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("parameters.fxml")));
        Scene scene = new Scene(root);
        nextpage.setTitle("Paramètres");
        nextpage.setScene(scene);
        nextpage.show();
    }

    @FXML
    protected void onFileButton() {
        Stage stage = (Stage) searchButton.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("All Files", "*.*"), new FileChooser.ExtensionFilter("JPG", "*.jpg"), new FileChooser.ExtensionFilter("PNG", "*.png"));

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
