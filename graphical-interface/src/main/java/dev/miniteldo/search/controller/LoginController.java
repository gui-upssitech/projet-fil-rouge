package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.view.Views;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;

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

    public void onOkButton(ActionEvent actionEvent) {
        // FIXME: 17/03/2022
        boolean isValidPassword = AppState.getInstance().getEngine().login(passwordField.getText());

        if (isValidPassword) {
            App.closeDialog();
            App.setView(Views.ADMIN_CONFIG);
        } else {
            passwordField.clear();
            passwordField.promptTextProperty().set("Erreur mot de passe incorrect ...");
        }
    }

    // Methods
}
