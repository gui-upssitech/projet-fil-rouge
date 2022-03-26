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
    private SearcherType requestType;

    @FXML
    public Label searchName;

    @FXML
    public VBox requestContainer;
    @FXML
    public VBox resultContainer;
    public ImageView returnButton;

    private HashMap<String, ArrayList<SearchResult>> hashMap = new HashMap<>();

    // Methods
    @FXML
    public void initialize() {
        initData();

        if (hashMap.isEmpty()) {
            Label label = new Label("Aucune sauvegarde dans le fichier");
            requestContainer.getChildren().add(label);
        } else {
            for (String request : hashMap.keySet()) {
                requestType = Tools.getRequestType(request);
                HBox result = SearchResultComponentFactory.createComponent(
                        Component.SEARCH,
                        request,
                        requestType,
                        null,
                        event -> onRequestClicked(request)
                );
                requestContainer.getChildren().add(result);
            }

            for (SearchResult searchResult : hashMap.entrySet().iterator().next().getValue()) {
                HBox result = SearchResultComponentFactory.createComponent(
                        Component.SEARCH_RESULT,
                        null,
                        requestType,
                        searchResult,
                        event -> onResultClicked(searchResult)
                );
                resultContainer.getChildren().add(result);
            }
        }
    }

    private void onRequestClicked(String request) {
        System.out.println("Requete" + request);

        resultContainer.getChildren().clear();
        for (SearchResult searchResult : hashMap.get(request)) {
            HBox result = SearchResultComponentFactory.createComponent(
                    Component.SEARCH_RESULT,
                    null,
                    requestType,
                    searchResult,
                    event -> onResultClicked(searchResult)
            );
            resultContainer.getChildren().add(result);
        }
    }


    /**
     *
     */
    private void initData() {
        hashMap = FileTools.readFile();
        System.out.println("");
    }

    private void onResultClicked(SearchResult searchResult) {
        System.out.println(searchResult);
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.PARAMETERS);
    }

    public void onEscapeAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE) || keyEvent.getCode().equals(KeyCode.ENTER)) {
            onReturnButton();
        }
    }
}
