package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.Component;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Classe SaveController ...
 * Date : 24/03/2022
 * Auteur : Julian
 */
public class SaveController {
    // Attributs

    @FXML
    public VBox requestContainer;
    @FXML
    public VBox resultContainer;
    public ImageView returnButton;

    private HashMap<String, ArrayList<SearchResult>> hashMap = new HashMap<>();
    private SearcherType selectedRequestType;

    // Methods
    @FXML
    public void initialize() {
        hashMap = FileTools.readFile();

        if (hashMap.isEmpty()) {
            Label label = new Label("Aucune sauvegarde dans le fichier !");
            requestContainer.getChildren().add(label);
        } else {
            for (String request : hashMap.keySet()) {
                selectedRequestType = Tools.getRequestType(request);
                HBox result = SearchResultComponentFactory.createComponent(
                        Component.SEARCH,
                        request,
                        selectedRequestType,
                        null,
                        event -> onRequestClicked(request)
                );
                requestContainer.getChildren().add(result);
            }

            displayResults(hashMap.entrySet().iterator().next().getValue());
        }
    }

    private void onRequestClicked(String request) {
        // Clear the result container
        resultContainer.getChildren().clear();
        displayResults(hashMap.get(request));
    }

    /**
     * Print the results of the request passed in param
     *
     * @param searchResults
     */
    private void displayResults(ArrayList<SearchResult> searchResults) {
        if (searchResults.isEmpty()) {
            Label label = new Label("Aucun résultat !");
            resultContainer.getChildren().add(label);
        }
        for (SearchResult searchResult : searchResults) {
            HBox result = SearchResultComponentFactory.createComponent(
                    Component.SEARCH_RESULT,
                    null,
                    selectedRequestType,
                    searchResult,
                    event -> onResultClicked(searchResult)
            );
            resultContainer.getChildren().add(result);
        }
    }

    private void onResultClicked(SearchResult searchResult) {
        System.out.println(searchResult);
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.PARAMETERS);
    }

    public void onEscapeAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE)) {
            onReturnButton();
        }
    }
}
