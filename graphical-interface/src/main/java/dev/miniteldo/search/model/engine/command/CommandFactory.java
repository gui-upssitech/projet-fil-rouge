package searchengine.command;

import searchengine.searcher.SearcherType;

public class CommandFactory {
    public static Command getCommand(SearcherType searcherType, String data) {
        Command command;

        switch(searcherType) {
            case TEXT_KEYWORD:
            case TEXT_PATH:
            case IMAGE_RGB_PATH:
            case IMAGE_NB_PATH:
            case AUDIO_PATH:
        }
    }
}
