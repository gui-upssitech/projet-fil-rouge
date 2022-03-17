package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;

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
    protected void onReturnButton() {
        App.setView(Views.PARAMETERS);
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
