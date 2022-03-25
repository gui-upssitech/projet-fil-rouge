package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.Component;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
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
        ArrayList<SearchResult> searchResults = new ArrayList<>();
        searchResults.add(new SearchResult("/home/juju/Bureau/projet-fil-rouge/data/text/22-Les_clubs_de_football_anglais_utf8.xml", 12));
        searchResults.add(new SearchResult("/home/juju/Bureau/projet-fil-rouge/data/text/13-Ligue_des_champions____Si_utf8.xml", 5));

        hashMap.put("football", searchResults);

        searchResults = new ArrayList<>();
        searchResults.add(new SearchResult("/home/juju/Bureau/projet-fil-rouge/data/text/22-Les_clubs_de_football_anglais_utf8.xml", 5));
        hashMap.put("football+club", searchResults);


        searchResults = new ArrayList<>();
        searchResults.add(new SearchResult("/home/juju/Bureau/projet-fil-rouge/data/text/22-Les_clubs_de_football_anglais_utf8.xml", 12));
        searchResults.add(new SearchResult("/home/juju/Bureau/projet-fil-rouge/data/text/13-Ligue_des_champions____Si_utf8.xml", 5));
        searchResults.add(new SearchResult("/home/juju/Bureau/projet-fil-rouge/data/text/27-Le_Stade_de_France_s_ouvre_utf8.xml", 5));
        hashMap.put("football+club", searchResults);

        searchResults = new ArrayList<>();
        searchResults.add(new SearchResult("58", 12));
        searchResults.add(new SearchResult("59", 12));
        searchResults.add(new SearchResult("60", 12));
        searchResults.add(new SearchResult("61", 12));
        searchResults.add(new SearchResult("62", 12));
        searchResults.add(new SearchResult("63", 12));
        hashMap.put("/home/juju/Bureau/projet-fil-rouge/data/image/NB/51.bmp", searchResults);
    }

    private void onResultClicked(SearchResult searchResult) {
        System.out.println(searchResult);
    }

    @FXML
    protected void onReturnButton() {
        App.setView(Views.PARAMETERS);
    }

}
