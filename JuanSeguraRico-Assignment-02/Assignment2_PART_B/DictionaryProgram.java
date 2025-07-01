import com.google.common.collect.HashMultimap;
import com.google.common.collect.Multimap;

import java.util.*;

enum DictionaryEntry {
    ARROW("Arrow", PartOfSpeech.NOUN, "Here is one arrow: <IMG> -=>> </IMG>"),
    BOOK("Book", PartOfSpeech.NOUN, "A set of pages."),
    BOOK2("Book", PartOfSpeech.NOUN, "A written work published in printed or electronic form."),
    BOOK3("Book", PartOfSpeech.VERB, "To arrange for someone to have a seat on a plane."),
    BOOK4("Book", PartOfSpeech.VERB, "To arrange something on a particular date."),
    DISTINCT("Distinct", PartOfSpeech.ADJECTIVE, "Familiar. Worked in Java."),
    DISTINCT2("Distinct", PartOfSpeech.ADJECTIVE, "Unique. No duplicates. Clearly different or of a different kind."),
    DISTINCT3("Distinct", PartOfSpeech.ADVERB, "Uniquely. Written \"distinctly\"."),
    DISTINCT4("Distinct", PartOfSpeech.NOUN, "A keyword in this assignment."),
    DISTINCT5("Distinct", PartOfSpeech.NOUN, "An advanced search option."),
    DISTINCT6("Distinct", PartOfSpeech.NOUN, "Distinct is a parameter in this assignment."),
    PLACEHOLDER("Placeholder", PartOfSpeech.ADJECTIVE, "To be updated..."),
    PLACEHOLDER2("Placeholder", PartOfSpeech.ADVERB, "To be updated..."),
    PLACEHOLDER3("Placeholder", PartOfSpeech.CONJUNCTION, "To be updated..."),
    PLACEHOLDER4("Placeholder", PartOfSpeech.INTERJECTION, "To be updated..."),
    PLACEHOLDER5("Placeholder", PartOfSpeech.NOUN, "To be updated..."),
    PLACEHOLDER6("Placeholder", PartOfSpeech.PREPOSITION, "To be updated..."),
    PLACEHOLDER7("Placeholder", PartOfSpeech.PRONOUN, "To be updated..."),
    PLACEHOLDER8("Placeholder", PartOfSpeech.VERB, "To be updated..."),
    REVERSE("Reverse", PartOfSpeech.ADJECTIVE, "On back side."),
    REVERSE2("Reverse", PartOfSpeech.ADJECTIVE, "Opposite to usual or previous arrangement."),
    REVERSE3("Reverse", PartOfSpeech.NOUN, "A dictionary program's parameter."),
    REVERSE4("Reverse", PartOfSpeech.NOUN, "Change to opposite direction."),
    REVERSE5("Reverse", PartOfSpeech.NOUN, "The opposite."),
    REVERSE6("Reverse", PartOfSpeech.VERB, "Change something to opposite."),
    REVERSE7("Reverse", PartOfSpeech.VERB, "Go back"),
    REVERSE8("Reverse", PartOfSpeech.VERB, "Revoke ruling."),
    REVERSE9("Reverse", PartOfSpeech.VERB, "Turn something inside out.");

    private final String word;
    private final PartOfSpeech partOfSpeech;
    private final String definition;

    DictionaryEntry(String word, PartOfSpeech partOfSpeech, String definition) {
        this.word = word;
        this.partOfSpeech = partOfSpeech;
        this.definition = definition;
    }

    public String getWord() {
        return word;
    }

    public PartOfSpeech getPartOfSpeech() {
        return partOfSpeech;
    }

    public String getDefinition() {
        return definition;
    }
}

enum PartOfSpeech {
    NOUN("n."),
    VERB("v."),
    ADJECTIVE("adj."),
    ADVERB("adv."),
    CONJUNCTION("conj."),
    INTERJECTION("interj."),
    PREPOSITION("prep."),
    PRONOUN("pron.");

    private final String abbreviation;

    PartOfSpeech(String abbreviation) {
        this.abbreviation = abbreviation;
    }

    public String getAbbreviation() {
        return abbreviation;
    }
}

public class DictionaryProgram {
    private final Multimap<String, DictionaryEntry> dictionary;

    public DictionaryProgram() {
        dictionary = HashMultimap.create();
        loadEntries();
    }

    public void loadEntries() {
        for (DictionaryEntry entry : DictionaryEntry.values()) {
            dictionary.put(entry.getWord(), entry);
        }
    }

    private List<DictionaryEntry> searchDictionary(String word, String partOfSpeech, boolean distinct, boolean reverse) {
        List<DictionaryEntry> results = new ArrayList<>();

        for (DictionaryEntry entry : DictionaryEntry.values()) {
            if (entry.getWord().equalsIgnoreCase(word) &&
                    (partOfSpeech == null || entry.getPartOfSpeech().name().equalsIgnoreCase(partOfSpeech))) {
                results.add(entry);
            }
        }

        if (distinct) {
            Set<DictionaryEntry> distinctResults = new HashSet<>(results);
            results = new ArrayList<>(distinctResults);
        }

        if (reverse) {
            Collections.reverse(results);
        }

        return results;
    }

    public static void main(String[] args) {
        DictionaryProgram dictionaryProgram = new DictionaryProgram();
        Scanner scanner = new Scanner(System.in);

        System.out.println("! Loading data...");
        System.out.println("! Loading completed...");
        System.out.println("===== DICTIONARY 340 JAVA =====");
        System.out.println("----- Keywords: 19");
        System.out.println("----- Definitions: 61");

        int searchCount = 1; // Initialize search count outside the loop

        while (true) {
            System.out.println("Search [" + searchCount + "]:");
            String input = scanner.nextLine();

            if (input.equalsIgnoreCase("!q")) {
                System.out.println("---THANK YOU---");
                break;
            }

            if (input.equalsIgnoreCase("!help") || input.trim().isEmpty()) {
                System.out.println("|");
                System.out.println("PARAMETER HOW-TO, please enter:");
                System.out.println("1. A search key -then");
                System.out.println("2. An optional part of speech -then");
                System.out.println("3. An optional 'distinct' -then");
                System.out.println("4. An optional 'reverse'");
                System.out.println("|");
                continue;
            }

            String[] params = input.split(" ");

            String word = params[0];
            String partOfSpeech = null;
            boolean distinct = false;
            boolean reverse = false;

            if (params.length > 1) {
                for (int i = 1; i < params.length; i++) {
                    String param = params[i];
                    if (param.equalsIgnoreCase("distinct")) {
                        distinct = true;
                    } else if (param.equalsIgnoreCase("reverse")) {
                        reverse = true;
                    } else {
                        partOfSpeech = param;
                    }
                }
            }

            List<DictionaryEntry> entries = dictionaryProgram.searchDictionary(word, partOfSpeech, distinct, reverse);

            if (entries.isEmpty()) {
                System.out.println("|");
                System.out.println("<NOT FOUND> To be considered for the next release. Thank you.");
                System.out.println("|");
            } else {
                for (DictionaryEntry entry : entries) {
                    System.out.println("|");
                    System.out.println(entry.getWord() + " [" + entry.getPartOfSpeech().name().toLowerCase() + "] : " + entry.getDefinition());
                    System.out.println("|");
                }
            }

            searchCount++; // Update search count after each search
        }
    }
}