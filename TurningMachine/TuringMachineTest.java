import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

public class TuringMachineTest {
    public static void main(String[] args) throws Exception {
        TuringMachine tm = TuringMachine.createTuringMachine(
                State.createState("start")
                        .addMap('#', "q0", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q0")
                        .addMap('o', "q0", State.Direction.RIGHT, null)
                        .addMap('+', "q1", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q1")
                        .addMap('o', "q1", State.Direction.RIGHT, null)
                        .addMap('=', "q2", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q2")
                        .addMap('o', "q2", State.Direction.RIGHT, null)
                        .addMap(null, "q9", State.Direction.LEFT, null)
        ).addState(
                State.createState("q3")
                        .addMap('#', "q4", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q4")
                        .addMap('x', "q4", State.Direction.RIGHT, null)
                        .addMap('+', "q4", State.Direction.RIGHT, null)
                        .addMap('o', "q5", State.Direction.RIGHT, 'x')
                        .addMap('=', "q6", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q5")
                        .addMap('o', "q5", State.Direction.RIGHT, null)
                        .addMap('+', "q5", State.Direction.RIGHT, null)
                        .addMap('=', "q7", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q6")
                        .addMap('x', "q6", State.Direction.RIGHT, null)
                        .addMap(null, "accept", State.Direction.RIGHT, null)
        ).addState(
                State.createState("q7")
                        .addMap('x', "q7", State.Direction.RIGHT, null)
                        .addMap('o', "q9", State.Direction.RIGHT, 'x')
        ).addState(
                State.createState("q9")
                        .addMap('+', "q9", State.Direction.LEFT, null)
                        .addMap('o', "q9", State.Direction.LEFT, null)
                        .addMap('=', "q9", State.Direction.LEFT, null)
                        .addMap('x', "q9", State.Direction.LEFT, null)
                        .addMap(null, "q9", State.Direction.LEFT, null)
                        .addMap('#', "q3", State.Direction.LEFT, null)
        ).addState(
                State.createAcceptState("accept")
        );

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str;
        while ((str = br.readLine()) != null) {
            tm.test(str);
        }
    }

    public static class TuringMachine {
        public State start;
        public Map<String, State> states = new HashMap<>();

        private TuringMachine() {
        }

        public static TuringMachine createTuringMachine(State start) {
            TuringMachine tm = new TuringMachine();
            tm.start = start;
            tm.addState(start);
            return tm;
        }

        public TuringMachine addState(State s) {
            this.states.put(s.name, s);
            return this;
        }

        public boolean test(String str) {
            ArrayList<Character> list = getList(str);
            int ptr = 0;

            State now = start;
            while (now.type != State.Type.ACCEPT) {
                System.out.println("当前状态：" + now.name + "，" +
                        "当前纸带：" + list.stream().map(it -> it == null ? "" : Character.toString(it)).collect(Collectors.joining()) + "，" +
                        "当前位置：" + ptr
                );

                Triple<String, State.Direction, Character> next = now.getMap(getNow(list, ptr));
                if (next == null) {
                    System.out.println("拒绝");
                    return false;
                }

                if (next.third != null) {
                    list.set(ptr, next.third);
                }
                ptr = next.second == State.Direction.RIGHT ? ptr + 1 : Math.max(ptr - 1, 0);
                now = states.get(next.first);
            }
            System.out.println("接受");
            return true;
        }

        private ArrayList<Character> getList(String str) {
            ArrayList<Character> list = new ArrayList<>();
            for (char c : str.toCharArray()) {
                list.add(c);
            }
            return list;
        }

        private Character getNow(ArrayList<Character> chs, int pos) {
            if (pos < 0) return null;
            if (pos >= chs.size()) {
                for (int i = chs.size(); i <= pos; ++i) {
                    chs.add(null);
                }
            }
            return chs.get(pos);
        }
    }

    public static class State {
        public String name;
        public Type type = Type.NORMAL;

        private State() {
        }

        public static State createState(String name) {
            State s = new State();
            s.name = name;
            return s;
        }

        public static State createAcceptState(String name) {
            State s = createState(name);
            s.type = Type.ACCEPT;
            return s;
        }

        public static State createDeclineState(String name) {
            State s = createState(name);
            s.type = Type.DECLINE;
            return s;
        }

        private Map<Character, Triple<String, Direction, Character>> map = new HashMap<>();

        public State addMap(Character c, String toState, Direction direction, Character toChar) {
            map.put(c, Triple.from(toState, direction, toChar));
            return this;
        }

        public Triple<String, Direction, Character> getMap(Character c) {
            return map.get(c);
        }

        enum Direction {
            LEFT, RIGHT
        }

        enum Type {
            NORMAL, ACCEPT, DECLINE
        }
    }

    static class Triple<A, B, C> {
        A first;
        B second;
        C third;

        static <E, F, G> Triple<E, F, G> from(E first, F second, G third) {
            Triple<E, F, G> triple = new Triple<>();
            triple.first = first;
            triple.second = second;
            triple.third = third;
            return triple;
        }
    }
}
