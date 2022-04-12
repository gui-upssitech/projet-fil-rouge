module dev.miniteldo.search {
    requires javafx.controls;
    requires javafx.fxml;
    requires org.controlsfx.controls;

    requires java.desktop;

    requires org.kordamp.bootstrapfx.core;
    requires java.xml;
    requires javafx.media;

    opens dev.miniteldo.search to javafx.fxml;
    opens dev.miniteldo.search.controller to javafx.fxml, javafx.media, org.controlsfx.controls;

    exports dev.miniteldo.search.model.engines;
    exports dev.miniteldo.search.model.engines.miniteldoengine.searcher;

    exports dev.miniteldo.search;
    exports dev.miniteldo.search.view;
    exports dev.miniteldo.search.view.enums;
}