package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.Descriptor;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.TextDescriptor;
import dev.miniteldo.search.model.tools.FileTools;
import dev.miniteldo.search.view.SearchResultComponentFactory;
import dev.miniteldo.search.view.enums.Component;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 * Classe DescriptorController ...
 * Date : 27/03/2022
 * Auteur : Julian
 */
public class DescriptorController {
    // Attributs
    public TextField fileField;
    public VBox descriptorContainer;

    private HashMap<String, String> descriptor;

    public void onReturnButton(MouseEvent mouseEvent) {
        App.setView(Views.ADMIN_CONFIG);
    }

    public void onKeyAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE)) {
            App.setView(Views.ADMIN_CONFIG);
        }
    }

    public void onFileButton(ActionEvent event) {
        Stage stage = (Stage) fileField.getScene().getWindow();
        File file = FileTools.getInputFile(stage);

        if (file != null) {
            fileField.setText(file.toString());
        }
    }

    public void onVisualiserAction(ActionEvent event) {
        if (fileField.getText().isBlank()) {
            App.showDialog(Dialog.ERROR, "Problème, la requête est vide");
        } else {
            descriptorContainer.getChildren().clear();

            Descriptor d = AppState.getInstance().getEngine().viewDescriptor(fileField.getText());

            if (d instanceof TextDescriptor textDescriptor) {
                descriptor = textDescriptor.getDataDescriptor();

                for (Map.Entry<String, String> entry : descriptor.entrySet()) {
                    System.out.println(entry.getKey() + "/" + entry.getValue());

                    HBox result = createComponent(entry.getKey(), entry.getValue());

                    descriptorContainer.getChildren().add(result);
                }
            }

        }
    }

    private HBox createComponent(String word, String value) {
        HBox root;
        String componentPath = "/layout/" + Component.DESCRIPTOR.getPath();
        FXMLLoader fxmlLoader = new FXMLLoader(SearchResultComponentFactory.class.getResource(componentPath));

        try {
            root = (HBox) fxmlLoader.load();

            Label wordLabel = (Label) root.lookup("#wordLabel");
            Label valueLabel = (Label) root.lookup("#valueLabel");

            wordLabel.setText(word);
            valueLabel.setText(value);

        } catch (IOException e) {
            root = new HBox();
        }

        return root;
    }

}
