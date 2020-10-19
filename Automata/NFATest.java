import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

public class NFATest {

    public static void main(String[] args) throws Exception {
        NFA nfa = NFA.createNFA(
                State.createState("q1")
                        .addMap('0', "q1")
                        .addMap('1', "q1")
                        .addMap('1', "q2")
        ).addState(
                State.createState("q2")
                        .addMap('0', "q3")
                        .addMap(null, "q3")
        ).addState(
                State.createState("q3")
                        .addMap('1', "q4")
        ).addState(
                State.createEndState("q4")
                        .addMap('0', "q4")
                        .addMap('1', "q4")
        );

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str;
        while ((str = br.readLine()) != null) {
            nfa.test(str);
        }
    }

    public static class NFA {
        public State start;
        public Map<String, State> states = new HashMap<>();

        private NFA() {
        }

        public static NFA createNFA(State start) {
            NFA nfa = new NFA();
            nfa.start = start;
            nfa.addState(start);
            return nfa;
        }

        public NFA addState(State s) {
            this.states.put(s.name, s);
            return this;
        }

        public boolean test(String str) {
            char[] ch = str.toCharArray();
            int ptr = 0;

            Set<State> now = new HashSet<>();
            now.add(start);
            System.out.println("初始状态集合：{" + now.stream().map(it -> it.name).collect(Collectors.joining(", ")) + "}");

            if (processEmpty(now)) {
                System.out.println("读取一个或多个空字符后的状态集合：{" + now.stream().map(it -> it.name).sorted().collect(Collectors.joining(", ")) + "}");
            }

            for (final char cc : ch) {
                now = now.stream().map(it -> it.getMap(cc).stream()).flatMap(it -> it).map(it -> states.get(it)).collect(Collectors.toSet());
                System.out.println("读取字符" + cc + "后的状态集合：{" + now.stream().map(it -> it.name).sorted().collect(Collectors.joining(", ")) + "}");

                if (now.isEmpty()) {
                    System.out.println("状态集合为空，拒绝字符串");
                    return false;
                }

                if (processEmpty(now)) {
                    System.out.println("读取一个或多个空字符后的状态集合：{" + now.stream().map(it -> it.name).sorted().collect(Collectors.joining(", ")) + "}");
                }
            }

            if (hasEnd(now)) {
                System.out.println("最终状态集合中存在一个或多个终态，接受字符串");
                return true;
            } else {
                System.out.println("最终状态集合中不存在终态，拒绝字符串");
                return false;
            }
        }

        private boolean processEmpty(Set<State> now) {
            int count0 = now.size();

            int count;
            do {
                count = now.size();
                now.addAll(now.stream().map(it -> it.getMap(null).stream()).flatMap(it -> it).map(it -> states.get(it)).collect(Collectors.toSet()));
            } while (count != now.size());

            return count0 != now.size();
        }

        private boolean hasEnd(Set<State> now) {
            return now.stream().anyMatch(it -> it.end);
        }
    }

    public static class State {
        public String name;
        public boolean end = false;

        private State() {
        }

        public static State createState(String name) {
            State s = new State();
            s.name = name;
            return s;
        }

        public static State createEndState(String name) {
            State s = createState(name);
            s.end = true;
            return s;
        }

        private Map<Character, Set<String>> map = new HashMap<>();

        public State addMap(Character c, String s) {
            getMap(c).add(s);
            return this;
        }

        public Set<String> getMap(Character c) {
            return map.computeIfAbsent(c, k -> new HashSet<>());
        }
    }
}
