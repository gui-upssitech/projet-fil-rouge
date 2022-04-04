package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.enums.Component;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
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
    public Button resetButton;

    private HashMap<String, ArrayList<SearchResult>> hashMap = new HashMap<>();
    private SearcherType selectedRequestType;

    // Methods
    @FXML
    public void initialize() {
        displayRequest();
    }

    public void displayRequest() {
        hashMap = FileTools.readFile();

        if (hashMap.isEmpty()) {
            Label label = new Label("Aucune sauvegarde dans le fichier !");
            requestContainer.getChildren().add(label);
        } else {
            for (String request : hashMap.keySet()) {
                selectedRequestType = Tools.getRequestType(request);
                HBox result = SearchResultComponentFactory.createComponent(Component.SEARCH, request, selectedRequestType, null, event -> onRequestClicked(request));
                requestContainer.getChildren().add(result);
            }

            selectedRequestType = Tools.getRequestType(hashMap.entrySet().iterator().next().getKey());
            displayResults(hashMap.entrySet().iterator().next().getValue(), selectedRequestType);
        }
    }

    private void onRequestClicked(String request) {
        // Clear the result container
        resultContainer.getChildren().clear();

        selectedRequestType = Tools.getRequestType(request);
        displayResults(hashMap.get(request), selectedRequestType);
    }

    /**
     * Print the results of the request passed in param
     *
     * @param searchResults
     */
    private void displayResults(ArrayList<SearchResult> searchResults, SearcherType type) {
        if (searchResults.isEmpty()) {
            Label label = new Label("Aucun résultat !");
            resultContainer.getChildren().add(label);
        }
        for (SearchResult searchResult : searchResults) {
            HBox result = SearchResultComponentFactory.createComponent(Component.SEARCH_RESULT, null, type, searchResult, event -> onResultClicked(searchResult));
            result.setMaxWidth(Double.MAX_VALUE);
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

    public void onResetButton() {
        // Delete the file content
        if (!AppState.getInstance().isPopUp()) {
            boolean isClear = FileTools.clearFile();

            if (isClear) {
                resultContainer.getChildren().clear();
                requestContainer.getChildren().clear();
                displayRequest();

                App.showDialog(Dialog.SUCCESS, "Fichier de sauvegarde vidé !");
            } else {
                App.showDialog(Dialog.ERROR, "Problème à la suppression des données de sauvegarde");
            }
        }
    }


}
