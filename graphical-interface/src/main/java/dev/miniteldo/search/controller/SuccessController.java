package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;

/**
 * Classe SuccessController ...
 * Date : 25/03/2022
 * Auteur : Julian
 */
public class SuccessController {
    // Attributs
    public Label labelMessage;
    public Button okButton;

    @FXML
    public void initialize() {
        labelMessage.setText(AppState.getInstance().getSuccessMessage());
    }

    public void onOkButton() {
        App.closeDialog();
    }

    public void onEscapeAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE) || keyEvent.getCode().equals(KeyCode.ENTER)) {
            onOkButton();
        }
    }
}
