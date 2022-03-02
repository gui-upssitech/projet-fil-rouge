package com.example.demo;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;

public class ParameterController {
    @FXML
    public Button loginButton;
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
        }
    }
}
