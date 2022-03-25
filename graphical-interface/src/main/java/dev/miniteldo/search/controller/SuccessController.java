package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

/**
 * Classe SuccessController ...
 * Date : 25/03/2022
 * Auteur : Julian
 */
public class SuccessController {
    // Attributs
    public Label labelMessage;
    public Button okButton;

    public void onOkButton(ActionEvent event) {
        App.closeDialog();
    }
}
