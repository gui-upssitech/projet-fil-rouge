package dev.miniteldo.search.controller;

// Project : graphical-interface

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;

/**
 * Classe ErrorController ...
 * Date : 05/03/2022
 * Auteur : Julian
 */
public class ErrorController {
    // Attributs
    public Button okButton;
    public Label labelError;

    // Constructor
    public ErrorController() {
        // TODO
    }

    // Methods
    public void onOkButton() {
        Stage stage = (Stage) okButton.getScene().getWindow();
        stage.close();
    }

}
