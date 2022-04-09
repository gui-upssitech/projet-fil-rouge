package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Spinner;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.Map;

/**
 * Classe ErrorController ...
 * Date : 05/03/2022
 * Auteur : Julian
 */
public class ErrorController {
    // Attributs
    public Button okButton;
    public Label labelError;

    @FXML
    public void initialize() {
        labelError.setText(AppState.getInstance().getErrorMessage());
    }

    // Methods
    public void onOkButton() {
        App.closeDialog();
    }
}
