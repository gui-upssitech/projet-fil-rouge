package com.example.demo;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;


public class MainMenuController {

    public TextField searchBar;
    public Button searchButton;
    public Label messError;

    @FXML
    protected void onSearchButton() {

        // TODO ADD EXISTING AND CORRECT FILE CHECK
        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {
            messError.setText("Erreur, votre requête est vide");
        } else {
            // TODO CHECK TYPE OF RESEARCH WITH A SWITCH ON COMBOBOX
            messError.setText("Votre requête contient : \"" + searchBar.getText() + "\"");
        }
    }

}
