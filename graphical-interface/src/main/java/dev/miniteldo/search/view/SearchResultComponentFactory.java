package dev.miniteldo.search.view;

import dev.miniteldo.search.model.engines.AudioSearchResult;
import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.view.enums.Component;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;

import java.io.IOException;
import java.net.URL;

/**
 * class: SearchResultViewFactory
 * author: Guillaume Roussin
 * date: 20/03/2022
 */
public class SearchResultComponentFactory {

    // Methods
    public static HBox createComponent(Component component, String request, SearcherType type, SearchResult result, EventHandler<MouseEvent> onClick) {
        // Variables
        HBox root;
        String componentPath = "/layout/" + component.getPath();
        FXMLLoader fxmlLoader = new FXMLLoader(SearchResultComponentFactory.class.getResource(componentPath));

        switch (component) {
            case SEARCH_RESULT -> {
                try {
                    root = (HBox) fxmlLoader.load();

                    ImageView icon = (ImageView) root.lookup("#icon");
                    Label fileName = (Label) root.lookup("#file_name");
                    Label confidence = (Label) root.lookup("#confidence");

                    fileName.setText(getFileName(result, type));
                    confidence.setText(getConfidenceText(result.getConfidence(), type));
                    icon.setImage(getIcon(type));
                    root.setOnMouseClicked(onClick);

                } catch (IOException e) {
                    root = new HBox();
                }
            }
            case SEARCH -> {
                try {
                    root = (HBox) fxmlLoader.load();
                    ImageView icon = (ImageView) root.lookup("#icon");
                    Label fileName = (Label) root.lookup("#searchName");

                    fileName.setText(request);
                    icon.setImage(getIcon(type));
                    root.setOnMouseClicked(onClick);

                } catch (IOException e) {
                    root = new HBox();
                }
            }
            default -> {
                root = null;
            }
        }

        return root;
    }

    private static String getFileName(SearchResult result, SearcherType type) {
        String path = result.getFilePath();
        String file = path.substring(path.lastIndexOf('/') + 1);

        if (file.lastIndexOf('.') == -1)
            return path;

        String name = file
                .substring(0, file.lastIndexOf('.'))
                .replace("_utf8", "")
                .replaceAll("_+", " ");

        if(type == SearcherType.AUDIO_PATH) {
            AudioSearchResult audioResult = (AudioSearchResult) result;
            name += " (" + audioResult.getTimeCode() + "s)";
        }
        // FIXME: 24/03/2022 CHECK IF WE ARE IN THE CURRENT REP

        return name;
    }

    private static String getConfidenceText(float confidence, SearcherType type) {
        return (type.toString().startsWith("TEXT")) ? ""+confidence : confidence + "%";
    }

    private static Image getIcon(SearcherType type) {
        String path = "/images/icons/";

        if(type.toString().startsWith("TEXT"))
            path += "file-text.png";
        else if(type.toString().startsWith("IMAGE"))
            path += "image.png";
        else
            path += "music.png";

        URL url = SearchResultComponentFactory.class.getResource(path);
        return (url == null) ? null : new Image(url.toExternalForm());
    }

}