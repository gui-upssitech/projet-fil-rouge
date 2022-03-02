package com.example.demo;

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
    protected void onLoginButton() throws IOException {
        // TODO ACTION BUTTON LOGIN
        if (passwordField.getText() == null || passwordField.getText().trim().isEmpty()) {
            System.out.println("Erreur password empty");
        } else {
            System.out.println("Password valid");
            // Close the current page
            Stage stage = (Stage) returnButton.getScene().getWindow();
            stage.close();

            // load a new page
            Stage nextpage = new Stage();
            Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("configuration.fxml")));
            Scene scene = new Scene(root);
            nextpage.setTitle("Configuration");
            nextpage.setScene(scene);
            nextpage.show();

        }
    }

    @FXML
    protected void onReturnButton() throws IOException {
        // Close the current page
        Stage stage = (Stage) returnButton.getScene().getWindow();
        stage.close();

        // load a new page
        Stage nextpage = new Stage();
        Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("main-menu.fxml")));
        Scene scene = new Scene(root);
        nextpage.setTitle("Moteur de recherche");
        nextpage.setScene(scene);
        nextpage.show();
    }
}
