package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.VBox;

public class ParameterController {

    // View attributes
    @FXML
    public VBox settingsBox;
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
        App.showDialog(Dialog.LOGIN, "");
    }

    @FXML
    protected void onThemeBarClicked() {
        state.toggleDarkMode();
        setThemeIcon();
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }

    @FXML
    protected void onSaveButton() {
        App.setView(Views.SAVE);
    }

    // Other methods
    private void setThemeIcon() {
        sunIcon.setVisible(!state.isDarkMode());
        moonIcon.setVisible(state.isDarkMode());
    }

    public void onKeyAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE)) {
            onReturnButton();
        }
    }
}
