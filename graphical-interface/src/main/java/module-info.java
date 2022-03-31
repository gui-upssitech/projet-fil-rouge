module dev.miniteldo.search {
    requires javafx.controls;
    requires javafx.fxml;

    requires java.desktop;

    requires org.kordamp.bootstrapfx.core;
    requires java.xml;
    requires javafx.media;

    opens dev.miniteldo.search to javafx.fxml;
    opens dev.miniteldo.search.controller to javafx.fxml, javafx.media;

    exports dev.miniteldo.search;
    exports dev.miniteldo.search.view;
    exports dev.miniteldo.search.view.enums;
}