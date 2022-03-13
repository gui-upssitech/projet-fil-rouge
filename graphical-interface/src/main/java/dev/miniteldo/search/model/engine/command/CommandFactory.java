package dev.miniteldo.search.model.engine.command;

import dev.miniteldo.search.model.engine.searcher.SearcherType;

public class CommandFactory {

    public static Command getCommand(SearcherType searcherType, String data) {
        return new Command(searcherType.getSearcherType(), searcherType.getDataType(), data);
    }
}
