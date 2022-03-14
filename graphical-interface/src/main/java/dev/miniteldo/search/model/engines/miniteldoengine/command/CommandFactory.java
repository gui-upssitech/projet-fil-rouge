package dev.miniteldo.search.model.engines.miniteldoengine.command;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;

public class CommandFactory {

    public static Command getCommand(SearcherType searcherType, String data) {
        return new Command(searcherType.getSearcherType(), searcherType.getDataType(), data);
    }
}
