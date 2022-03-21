package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public class SearchController {
    @FXML public Button saveButton;
    @FXML public Button returnButton;

    @FXML private VBox resultContainer;

    public void initialize() {
        ArrayList<SearchResult> liste = AppState.getInstance().getCurrentRequest();
        displayResults(liste);
    }

    private void displayResults(ArrayList<SearchResult> liste) {
        if(liste.isEmpty())
            resultContainer.getChildren().add(new Label("No results found"));
        else {
            for (SearchResult searchResult : liste) {
                HBox result = SearchResultComponentFactory.createComponent(
                        SearcherType.TEXT_KEYWORD,
                        searchResult,
                        event -> onResultClicked(searchResult)
                );
                resultContainer.getChildren().add(result);
            }
        }
    }

    private void onResultClicked(SearchResult result) {
        System.out.println("Clicked result : " + result.getFilePath());
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.MAIN);
    }

    @FXML
    protected void onSaveButton() {

    }
}
