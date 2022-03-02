package com.example.demo;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;


public class MainMenuController {
    public TextField searchBar;
    public Button searchButton;
    public Label messError;

    @FXML
    protected void onSearchButton() throws IOException {
        // TODO ADD EXISTING AND CORRECT FILE CHECK
        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {
            messError.setText("Erreur, votre requête est vide");
        } else {
            // TODO CHECK TYPE OF RESEARCH WITH A SWITCH ON COMBOBOX
            messError.setText("Votre requête contient : \"" + searchBar.getText() + "\"");

            // Close the current page
            Stage stage = (Stage) searchBar.getScene().getWindow();
            stage.close();

            // load a new page
            Stage nextpage = new Stage();
            Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("result-search.fxml")));
            Scene scene = new Scene(root);
            nextpage.setTitle("Résultat recherche");
            nextpage.setScene(scene);
            nextpage.show();

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
}
