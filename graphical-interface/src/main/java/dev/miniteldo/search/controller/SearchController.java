package dev.miniteldo.search.controller;

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
    protected void onReturnButton() throws IOException {
        // Close the current page
        Stage stage = (Stage) returnButton.getScene().getWindow();
        stage.close();

        // load a new page
        Stage nextpage = new Stage();
        Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("/layout/main-menu.fxml")));
        Scene scene = new Scene(root);
        nextpage.setTitle("Moteur de recherche");
        nextpage.setScene(scene);
        nextpage.show();
    }
}
