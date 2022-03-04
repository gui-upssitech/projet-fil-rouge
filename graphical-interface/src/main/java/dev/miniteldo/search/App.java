package dev.miniteldo.search;

import dev.miniteldo.search.view.Views;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
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

    // -------------------------------

    private static Stage stage;

    @Override
    public void start(Stage stage) {
        App.stage = stage;

        stage.setTitle("Moteur de recherche");
        setView(Views.MAIN);

        stage.show();
    }

    public static void setView(Views view) {
        if(stage == null) return;

        String path = "/layout/" + view.getPath();
        try {

            FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(path));
            Scene scene = new Scene(fxmlLoader.load());
            stage.setScene(scene);

        } catch (IOException e) {
            System.out.println("Err: failed to change the view");
            e.printStackTrace();
        }

    }

}