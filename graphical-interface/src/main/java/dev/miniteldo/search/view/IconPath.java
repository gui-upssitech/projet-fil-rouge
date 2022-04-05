package dev.miniteldo.search.view;

import dev.miniteldo.search.model.AppState;
import javafx.beans.property.StringProperty;
import javafx.scene.Node;

/**
 * class: IconPath
 * author: Guillaume Roussin
 * date: 05/04/2022
 */
public class IconPath extends Node {

    private StringProperty path;

    public String getPath() {
        setPath(AppState.getInstance().getImageFolder());
        return path.get();
    }

    public void setPath(String path) {
        this.path.set(path);
    }

    public StringProperty pathProperty() {
        return path;
    }



}