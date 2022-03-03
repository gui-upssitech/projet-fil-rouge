package com.miniteldo;

// Project : graphical-interface

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

/**
 * Classe ConfigurationController ...
 * Date : 02/03/2022
 * Auteur : Julian
 */
public class ConfigurationController {
    // Attributs
    public Button validButton;
    public ProgressBar progressBar;
    public Label labelIndexation;
    public Button returnButton;

    // Methods
    @FXML
    protected void onReturnButton() throws IOException {
        // Close the current page
        Stage stage = (Stage) returnButton.getScene().getWindow();
        stage.close();

        // load a new page
        Stage nextpage = new Stage();
        Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("parameters.fxml")));
        Scene scene = new Scene(root);
        nextpage.setTitle("Paramètres");
        nextpage.setScene(scene);
        nextpage.show();
    }

    @FXML
    protected void onValidButton() {
        labelIndexation.setText("Indexation en cours ...");
        progressBar.setProgress(ProgressBar.INDETERMINATE_PROGRESS);
//        try {
//            Thread.sleep(1000);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//        labelIndexation.setText("Indexation terminé !");
//        progressBar.setProgress(0);
    }


}
