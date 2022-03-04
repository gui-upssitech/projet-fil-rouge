package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

public class SearchController {
    @FXML
    public Button saveButton;
    @FXML
    public Button returnButton;


    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }
}
