package dev.miniteldo.search;

import dev.miniteldo.search.view.Dialog;
import dev.miniteldo.search.view.Views;
import javafx.application.Application;
import javafx.event.EventType;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

/**
 * class: App
 * author: Guillaume Roussin
 * date: 04/03/2022
 */
public class App extends Application {

    // Main
    public static void main(String[] args) {
        App.launch();
    }

    // ---------------------------------------

    private static Stage stage;
    private static boolean darkMode = false;

    @Override
    public void start(Stage stage) {
        App.stage = stage;

        stage.setTitle("Minteldo");
        //stage.setResizable(false);
        setView(Views.MAIN);

        stage.show();
    }

    public static void setView(Views view) {
        if (stage == null) return;

        String path = "/layout/" + view.getPath();
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(path));
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

        } catch (IOException | NullPointerException e) {
            System.out.println("Err: failed to change the view");
            e.printStackTrace();
        }
    }

    public static void closeDialog() {
        if (stage == null) return;

        Node dialog = stage.getScene().lookup("#dialog");
        if(dialog != null) {
            Pane parent = (Pane) dialog.getParent();
            parent.getChildren().remove(dialog);
        }
    }

    public static void showDialog(Dialog dialog) {
        if (stage == null) return;

        String path = "/layout/" + dialog.getPath();
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(path));

            Pane rootPane = (Pane) stage.getScene().getRoot();
            Node dialogContent = fxmlLoader.load();

            VBox dialogRoot = new VBox();
            dialogRoot.setId("dialog");
            dialogRoot.setAlignment(Pos.CENTER);
            dialogRoot.setFillWidth(false);

            AnchorPane.setTopAnchor(dialogRoot, 0.0);
            AnchorPane.setBottomAnchor(dialogRoot, 0.0);
            AnchorPane.setLeftAnchor(dialogRoot, 0.0);
            AnchorPane.setRightAnchor(dialogRoot, 0.0);

            dialogRoot.setOnMouseClicked(event -> closeDialog());

            dialogRoot.getChildren().add(dialogContent);
            rootPane.getChildren().add(dialogRoot);

        } catch (IOException | NullPointerException e) {
            System.out.println("Err: failed to change the view");
            e.printStackTrace();
        }
    }
}