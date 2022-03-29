package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

import java.io.File;

/**
 * Classe MainMenuController ...
 * Date : 02/03/2022
 * Auteur : all
 */
public class MainMenuController {
    public TextField searchBar;
    public Button searchButton;
    public Label infoLabel;
    public ImageView infoImage;
    private String request;

    private boolean isInfoUp = false;

    @FXML
    public void initialize() {
        infoImage.addEventHandler(MouseEvent.MOUSE_ENTERED, e -> infoLabel.setVisible(true));
        infoImage.addEventHandler(MouseEvent.MOUSE_EXITED, e -> infoLabel.setVisible(false));
    }

    @FXML
    protected void onSearchButton(ActionEvent event) {
        request = searchBar.getText().trim();

        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {
            App.showDialog(Dialog.ERROR, "Problème, la requête vide !");
        } else {
            if (!Tools.isRequestValid(request)) {
                App.showDialog(Dialog.ERROR, "Problème, la requête n'est pas valide !");
            } else {
                AppState.getInstance().setCurrentRequest(searchBar.getText().trim());
                App.setView(Views.SEARCH_RESULT);
            }
        }
    }

    @FXML
    protected void onParamButton() {
        App.setView(Views.PARAMETERS);
    }

    @FXML
    protected void onFileButton() {
        Stage stage = (Stage) searchButton.getScene().getWindow();
        File file = FileTools.getInputFile(stage);

        if (file != null) {
            searchBar.setText(file.toString());
        }
    }

    public void onInfoAction(MouseEvent mouseEvent) {
        infoLabel.setVisible(!isInfoUp);
        isInfoUp = !isInfoUp;
    }

    public void onEnterAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            onSearchButton(null);
        }
    }
}
