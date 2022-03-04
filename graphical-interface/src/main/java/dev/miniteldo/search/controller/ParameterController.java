package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

public class ParameterController {

    @FXML
    public Button loginButton;
    public Button returnButton;
    @FXML
    private CheckBox adminButton;
    @FXML
    private PasswordField passwordField;

    @FXML
    protected void onAdminButton() {
        if (adminButton.isSelected()) {
            passwordField.setVisible(true);
            loginButton.setVisible(true);
        } else {
            passwordField.setVisible(false);
            loginButton.setVisible(false);
        }
    }

    @FXML
    protected void onLoginButton() {
        // TODO ACTION BUTTON LOGIN
        if (passwordField.getText() == null || passwordField.getText().trim().isEmpty()) {
            System.out.println("Erreur password empty");
        } else {
            System.out.println("Password valid");
            App.setView(Views.ADMIN_CONFIG);
        }
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }
}
