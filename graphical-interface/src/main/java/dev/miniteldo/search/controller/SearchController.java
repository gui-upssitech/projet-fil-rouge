package dev.miniteldo.search.controller;

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.view.Views;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;

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
        textArea.setText(AppState.getInstance().getCurrentRequest().toString());
    }
}
