module dev.miniteldo.search {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.kordamp.bootstrapfx.core;

    opens dev.miniteldo.search to javafx.fxml;
    opens dev.miniteldo.search.controller to javafx.fxml;

    exports dev.miniteldo.search;
    exports dev.miniteldo.search.view;
}