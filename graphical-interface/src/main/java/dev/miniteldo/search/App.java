package dev.miniteldo.search;

import dev.miniteldo.search.model.AppState;
import dev.miniteldo.search.view.enums.Dialog;
import dev.miniteldo.search.view.enums.Views;
import javafx.application.Application;
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

        // TODO - Remove for testing only
        AppState.getInstance().setCurrentRequest("/var/code/uni/PFR/data/text/03-Mimer_un_signal_nerveux_pour_utf8.xml");
        stage.setMaximized(false);
        App.setView(Views.SEARCH_RESULT);

        //setView(Views.MAIN);

        //stage.setResizable(true);
        //stage.setMaximized(true);
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
        if (dialog != null) {
            Pane parent = (Pane) dialog.getParent();
            parent.getChildren().remove(dialog);
        }
    }

    public static void showDialog(Dialog dialog, String message) {
        AppState.getInstance().setDialogMessage(dialog, message);

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