package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.view.Dialog;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;

public class ParameterController {

    // View attributes

    @FXML
    public Button loginButton;
    @FXML
    public VBox settingsBox;
    @FXML
    private CheckBox adminButton;
    @FXML
    private PasswordField passwordField;
    @FXML
    private ImageView sunIcon, moonIcon;
    // Other attributes
    private AppState state;

    // FX Methods

    @FXML
    public void initialize() {
        state = AppState.getInstance();
        setThemeIcon();
    }

    @FXML
    protected void onAdminButton() {
        // TODO: launch login dialog
        App.showDialog(Dialog.LOGIN);
        System.out.println("Je ne suis pas bloqué dans le pop up...");
    }

//    @FXML
//    protected void onLoginButton(ActionEvent event) {
//        if (passwordField.getText() == null || passwordField.getText().trim().isEmpty()) {
//            System.out.println("Error blank text");
//            return;
//        }
//
//        String password = passwordField.getText().trim();
//        if (state.adminLogin(password)) {
//            System.out.println("Password valid");
//            App.setView(Views.ADMIN_CONFIG);
//        } else {
//            System.out.println("Error wrong password");
//            // TODO: error message
//        }
//    }

    @FXML
    protected void onThemeBarClicked() {
        state.toggleDarkMode();
        setThemeIcon();
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }

    // Other methods
    private void setThemeIcon() {
        sunIcon.setVisible(!state.isDarkMode());
        moonIcon.setVisible(state.isDarkMode());
    }
}
