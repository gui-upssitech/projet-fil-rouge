package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;

import java.util.ArrayList;

public class SearchController {
    @FXML
    public Button saveButton;
    @FXML
    public Button returnButton;
    public TextArea textArea;

    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }

    @FXML
    protected void onSaveButton() {
        String resultat = "";

        ArrayList<SearchResult> liste = AppState.getInstance().getCurrentRequest();
        for (SearchResult searchResult : liste) {
            resultat += "\n\r" + searchResult.toString();
        }
        textArea.setText(resultat);
    }
}
