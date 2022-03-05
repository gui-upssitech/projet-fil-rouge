package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.view.Error;
import dev.miniteldo.search.view.Views;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;

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
    protected void onLoginButton(ActionEvent event) {
        // TODO ACTION BUTTON LOGIN
        if (passwordField.getText() == null || passwordField.getText().trim().isEmpty()) {
            System.out.println("Erreur password empty");
            Error.popUpError(((Node) event.getSource()).getScene().getWindow(), "Login vide !");
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
