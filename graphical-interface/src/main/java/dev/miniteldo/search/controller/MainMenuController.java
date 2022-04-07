package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.EngineFactory;
import dev.miniteldo.search.model.engines.Engines;
import dev.miniteldo.search.model.engines.SearchEngine;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.TextSearcher;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.model.tools.Tools;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.animation.Animation;
import javafx.animation.RotateTransition;
import javafx.beans.InvalidationListener;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.controlsfx.control.CheckComboBox;
import org.controlsfx.control.textfield.TextFields;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Classe MainMenuController ...
 * Date : 02/03/2022
 * Auteur : all
 */
public class MainMenuController {
    @FXML
    public TextField searchBar;
    public Button searchButton;
    public Label infoLabel;
    public ImageView infoImage;
    public ImageView paramButton;
    public ComboBox<String> comboBox;
    public ColorPicker colorPicker;
    public CheckComboBox<Engines> checkCombo;

    private String request;

    @FXML
    public void initialize() {
        Engines curEngines = AppState.getInstance().getCurEngine();

        // Add hover to info icon
        infoImage.addEventHandler(MouseEvent.MOUSE_ENTERED, e -> infoLabel.setVisible(true));
        infoImage.addEventHandler(MouseEvent.MOUSE_EXITED, e -> infoLabel.setVisible(false));

        // Add animation to param image
        RotateTransition rotation = new RotateTransition(Duration.seconds(0.5), paramButton);
        rotation.setCycleCount(Animation.INDEFINITE);
        rotation.setByAngle(360);

        paramButton.setOnMouseEntered(e -> rotation.play());
        paramButton.setOnMouseExited(e -> rotation.pause());

        // ComboBox
        List<String> strings = new ArrayList<>();
        for (Engines engines : Engines.values()) {
            strings.add(engines.toString());
        }
        comboBox.setItems(FXCollections.observableArrayList(strings));
        comboBox.getSelectionModel().select(curEngines.toString());
        comboBox.valueProperty().addListener((options, oldValue, newValue) -> {
            AppState.getInstance().setEngine(Engines.valueOf(newValue));
        });

        // Auto completion
        TextSearcher textSearcher = (TextSearcher) SearcherFactory.getSearcher("search-engine", SearcherType.TEXT_COMPLETION);
        ArrayList<String> stringArrayList = new ArrayList<>();
        try {
            stringArrayList = textSearcher.getWordsList();
        } catch (IOException e) {
            e.printStackTrace();
        }
        TextFields.bindAutoCompletion(searchBar, stringArrayList.toArray());

        // Add check box
        System.out.println(AppState.getInstance().engines);
        for (Engines engines : AppState.getInstance().getAllEngines()) {
            checkCombo.getItems().add(engines);
        }

        checkCombo.getCheckModel().getCheckedItems().addListener(new ListChangeListener<Engines>() {
            public void onChanged(ListChangeListener.Change<? extends Engines> c) {
                AppState.getInstance().clearSelectedEngine();
                for (Engines engines : c.getList()) {
                    AppState.getInstance().addSelectedEngine(EngineFactory.createEngine(engines));
                }
                System.out.println(c);
                System.out.println(AppState.getInstance().getEnginesSelected());
            }
        });
    }


    @FXML
    protected void onSearchButton(ActionEvent event) {
        request = searchBar.getText().trim();

        if (searchBar.getText() == null || searchBar.getText().trim().isEmpty()) {
            if (!AppState.getInstance().isPopUp()) {
                App.showDialog(Dialog.ERROR, "Problème, la requête est vide !");
            }
        } else if (!AppState.getInstance().isPopUp()) {
            if (!Tools.isRequestValid(request)) {
                if (!AppState.getInstance().isPopUp())
                    App.showDialog(Dialog.ERROR, "Problème, requête invalide !");

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

    public void onEnterAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            onSearchButton(null);
        }
    }

    public void onColor2Action(ActionEvent event) {
        String temp = "#" + colorPicker.getValue().toString().toUpperCase().substring(2, 8);
        searchBar.setText(temp);
    }

}
