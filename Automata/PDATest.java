import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

public class PDATest {
    public static void main(String[] args) throws Exception {
        PDA pda = PDA.createDPA(
                State.createEndState("0")
                        .addMap('a', null, "0", "")
                        .addMap('b', 'C', "0", "")
                        .addMap('b', 'B', "0", "BB")
                        .addMap('b', '#', "0", "B#")
                        .addMap('c', 'B', "0", "")
                        .addMap('c', 'C', "0", "CC")
                        .addMap('c', '#', "0", "C#")
        );

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str;
        while ((str = br.readLine()) != null) {
            pda.test(str);
        }
    }

    public static class PDA {
        public State start;
        public Map<String, State> states = new HashMap<>();

        private PDA() {
        }

        public static PDA createDPA(State start) {
            PDA pda = new PDA();
            pda.start = start;
            pda.addState(start);
            return pda;
        }

        public PDA addState(State s) {
            this.states.put(s.name, s);
            return this;
        }

        public boolean test(String str) {
            char[] ch = str.toCharArray();
            int ptr = 0;

            State now = start;
            Deque<Character> stack = new LinkedList<>();
            stack.addFirst('#');
            System.out.println("初始状态：" + now.name + "，初始栈：" + stack.stream().map(c -> Character.toString(c)).collect(Collectors.joining()));

            for (final char cc : ch) {
                Pair<String, List<Character>> next = now.getMap(cc, null);
                if (next == null) {
                    next = now.getMap(cc, stack.pollFirst());
                }
                if (next == null) {
                    System.out.println("无转移条件，拒绝字符串");
                    return false;
                }

                now = states.get(next.first);
                next.second.forEach(stack::addFirst);

                System.out.println("读取字符" + cc + "后的状态：" + now.name + "，栈：" + stack.stream().map(c -> Character.toString(c)).collect(Collectors.joining()));
            }

            if (now.end && stack.peek() == '#') {
                System.out.println("最终状态为终态且最终栈只有初始符号，接受字符串");
                return true;
            } else if (!now.end) {
                System.out.println("最终状态不为终态，拒绝字符串");
                return false;
            } else {
                System.out.println("最终栈含有初始符号以外的符号，拒绝字符串");
                return false;
            }
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

        private Map<Character, Map<Character, Pair<String, List<Character>>>> map = new HashMap<>();

        public State addMap(Character c, Character fromStack, String toState, String toStack) {
            LinkedList<Character> list = new LinkedList<>();
            for (char cc : toStack.toCharArray()) {
                list.addFirst(cc);
            }
            map.computeIfAbsent(c, k -> new HashMap<>()).put(fromStack, Pair.from(toState, list));
            return this;
        }

        public Pair<String, List<Character>> getMap(Character c, Character fromStack) {
            return map.computeIfAbsent(c, k -> new HashMap<>()).get(fromStack);
        }
    }

    static class Pair<A, B> {
        A first;
        B second;

        void set(A first, B second) {
            this.first = first;
            this.second = second;
        }

        static <C, D> Pair<C, D> from(C first, D second) {
            Pair<C, D> pair = new Pair<>();
            pair.first = first;
            pair.second = second;
            return pair;
        }
    }
}
