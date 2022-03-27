package dev.miniteldo.search.controller;

// Project : graphical-interface

import dev.miniteldo.search.App;
import dev.miniteldo.search.view.enums.Views;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;

/**
 * Classe DescriptorController ...
 * Date : 27/03/2022
 * Auteur : Julian
 */
public class DescriptorController {
    // Attributs
    public Button textButton;
    public Button imageButton;
    public Button audioButton;
    public ScrollPane fileContainers;
    public ScrollPane descriptorContainer;

    public void onReturnButton(MouseEvent mouseEvent) {
        App.setView(Views.ADMIN_CONFIG);
    }

    public void onKeyAction(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ESCAPE)) {
            App.setView(Views.ADMIN_CONFIG);
        }
    }

    public void onTextButton(ActionEvent event) {
        System.out.println("Text");
    }

    public void onImageButton(ActionEvent event) {
        System.out.println("Image");
    }

    public void onAudioButton(ActionEvent event) {
        System.out.println("Audio");
    }
}
