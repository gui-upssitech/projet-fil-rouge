package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.view.enums.Views;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;

/**
 * Classe LoginController ...
 * Date : 17/03/2022
 * Auteur : Julian
 */
public class LoginController {

    // Attributs
    public Button okButton;
    public PasswordField passwordField;
    public Label labelLogin;

    // Methods
    public void onOkButton() {
        boolean isValidPassword = AppState.getInstance().getEngine().login(passwordField.getText());

        if (isValidPassword) {
            App.closeDialog();
            App.setView(Views.ADMIN_CONFIG);
        } else {
            passwordField.clear();
            passwordField.promptTextProperty().set("Erreur mot de passe incorrect ...");
        }
    }

    public void onEnterAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            onOkButton();
        }
    }
}
