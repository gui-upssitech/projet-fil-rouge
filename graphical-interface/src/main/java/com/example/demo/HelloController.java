package com.example.demo;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.stage.Stage;

public class HelloController {
    @FXML
    private Label welcomeText;
    @FXML
    private javafx.scene.control.Button closeButton;

    @FXML
    protected void onHelloButtonClick() {
        // get a handle to the stage
        Stage stage = (Stage) closeButton.getScene().getWindow();
        // do what you have to do
        welcomeText.setText("Welcome to JavaFX Application!");

        stage.close();

        
    }
}