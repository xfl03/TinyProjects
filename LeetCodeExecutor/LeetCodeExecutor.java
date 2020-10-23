import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class LeetCodeExecutor {
    static Method method = null;
    static Object solution = null;

    public static void main(String... args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str;
        while (!"".equals(str = br.readLine())) {
            System.out.println(invoke(str));
        }
    }

    static String invoke(String str) {
        Data data = toData(str);
        if (method == null) {
            initMethod(data);
        }
        if (method == null) {
            System.err.println(String.format("No method found for '%s'.", data.toTypeString()));
            return "";
        }
        Object ret = data.invoke(method, solution);
        if (ret instanceof ListNode) {
            StringBuilder builder = new StringBuilder();
            return printListNode(builder, (ListNode) ret).toString();
        }
        if (ret.getClass().isArray()) {
            StringBuilder builder = new StringBuilder();
            return printArray(builder, ret).toString();
        }
        return ret.toString();
    }

    static StringBuilder printListNode(StringBuilder builder, ListNode node) {
        while (node!= null) {
            builder.append(node.val);
            if (node.next != null) {
                builder.append("->");
            }
            node = node.next;
        }
        return builder;
    }

    static StringBuilder printArray(StringBuilder builder, Object array) {
        builder.append("[");
        if (array instanceof int[][]) {
            int[][] arr = (int[][]) array;
            for (int i = 0; i < arr.length; ++i) {
                printArray(builder, arr[i]);
                if (i != arr.length - 1) {
                    builder.append(", ");
                }
            }
        } else if (array instanceof int[]) {
            int[] arr = (int[]) array;
            for (int i = 0; i < arr.length; ++i) {
                builder.append(arr[i]);
                if (i != arr.length - 1) {
                    builder.append(", ");
                }
            }
        } else {
            Object[] arr = (Object[]) array;
            for (int i = 0; i < arr.length; ++i) {
                builder.append(arr[i]);
                if (i != arr.length - 1) {
                    builder.append(", ");
                }
            }
        }
        builder.append("]");
        return builder;
    }

    static void initMethod(Data data) {
        try {
            Class<?> clazz = Class.forName("Solution");
            solution = clazz.newInstance();
            Method[] methods = clazz.getMethods();
            for (Method m : methods) {
                if (data.canAccept(m)) {
                    method = m;
                }
            }
        } catch (ClassNotFoundException e) {
            System.err.println("Class 'Solution' not found.");
        } catch (IllegalAccessException | InstantiationException e) {
            System.err.println("Class 'Solution' doesn't have default constructor.");
        }
    }

    enum Status {
        WAITING,
        WAITING_VALUE,
        READING_INT,
        READING_STRING,
        WAITING_ARRAY,
        READING_INT_ARRAY,
        READING_STRING_ARRAY,
        WAITING_LIST,
        READING_INT_LIST
    }

    static Data toData(String s) {
        Data data = new Data();
        Status status = Status.WAITING;

        StringBuilder buffer = new StringBuilder();

        int arrayDepth = 0;
        Stack<List<Object>> listBuffer = new Stack<>();
        List<Integer> listBuffer2 = new ArrayList<>();
        Object[] typeBuffer = new Object[0];

        for (char c : s.toCharArray()) {
            switch (status) {
                case WAITING:
                    if (c == '"') {
                        status = Status.READING_STRING;
                        buffer = new StringBuilder();
                    } else if (c == '[') {
                        status = Status.WAITING_ARRAY;
                        listBuffer.add(new ArrayList<>());
                        arrayDepth = 1;
                    } else if (c == '-' || isNum(c)) {
                        status = Status.READING_INT;
                        buffer = new StringBuilder();
                        buffer.append(c);
                    } else if (isLetter(c)) {
                        status = Status.WAITING_VALUE;
                    }
                    break;
                case WAITING_VALUE:
                    if (c == '=') {
                        status = Status.WAITING;
                    }
                    break;
                case READING_INT:
                    if (isNum(c)) {
                        buffer.append(c);
                    } else if (c == '-') {
                        listBuffer2.clear();
                        listBuffer2.add(Integer.parseInt(buffer.toString()));
                        status = Status.WAITING_LIST;
                    } else {
                        data.add(Integer.parseInt(buffer.toString()));
                        status = Status.WAITING;
                    }
                    break;
                case READING_STRING:
                    if (c == '"') {
                        data.add(buffer.toString());
                        status = Status.WAITING;
                    } else {
                        buffer.append(c);
                    }
                    break;
                case WAITING_ARRAY:
                    if (c == '"') {
                        status = Status.READING_STRING_ARRAY;
                        buffer = new StringBuilder();
                        typeBuffer = new String[0];
                    } else if (c == '[') {
                        arrayDepth = 2;
                        listBuffer.add(new ArrayList<>());
                    } else if (c == ']') {
                        status = arrayStore(arrayDepth, listBuffer, data, typeBuffer);
                    } else if (c == '-' || isNum(c)) {
                        status = Status.READING_INT_ARRAY;
                        buffer = new StringBuilder();
                        buffer.append(c);
                        typeBuffer = new Integer[0];
                    }
                    break;
                case READING_INT_ARRAY:
                    if (isNum(c)) {
                        buffer.append(c);
                    } else {
                        listBuffer.peek().add(Integer.parseInt(buffer.toString()));
                        if (c == ']') {
                            status = arrayStore(arrayDepth, listBuffer, data, typeBuffer);
                        } else {
                            status = Status.WAITING_ARRAY;
                        }
                    }
                    break;
                case READING_STRING_ARRAY:
                    if (c == '"') {
                        listBuffer.peek().add(buffer.toString());
                        status = Status.WAITING_ARRAY;
                    } else {
                        buffer.append(c);
                    }
                    break;
                case WAITING_LIST:
                    if (c == '-' || isNum(c)) {
                        status = Status.READING_INT_LIST;
                        buffer = new StringBuilder();
                        buffer.append(c);
                    }
                    break;
                case READING_INT_LIST:
                    if (isNum(c)) {
                        buffer.append(c);
                    } else if (c == '-') {
                        listBuffer2.add(Integer.parseInt(buffer.toString()));
                        status = Status.WAITING_LIST;
                    } else {
                        listBuffer2.add(Integer.parseInt(buffer.toString()));
                        data.add(toListNode(listBuffer2));
                        status = Status.WAITING;
                    }
            }
        }
        if (status == Status.READING_INT) {
            data.add(Integer.parseInt(buffer.toString()));
        } else if (status == Status.READING_INT_LIST) {
            listBuffer2.add(Integer.parseInt(buffer.toString()));
            data.add(toListNode(listBuffer2));
        }
        return data;
    }

    static Status arrayStore(int arrayDepth, Stack<List<Object>> listBuffer, Data data, Object[] typeBuffer) {
        if (listBuffer.size() == 1) {
            List<Object> list = listBuffer.pop();
            if (arrayDepth == 1) {
                if (typeBuffer.getClass().getComponentType() == Integer.class) {
                    int[] arr = new int[list.size()];
                    for (int j = 0; j < arr.length; ++j) {
                        arr[j] = (int) list.get(j);
                    }
                    data.add(arr);
                } else {
                    data.add(list.toArray(typeBuffer));
                }
            } else {
                if (typeBuffer.getClass().getComponentType() == Integer.class) {
                    int[][] arr = new int[list.size()][];
                    for (int i = 0; i < arr.length; ++i) {
                        List<Object> list2 = (List<Object>) list.get(i);
                        int[] arr2 = new int[list2.size()];
                        for (int j = 0; j < arr2.length; ++j) {
                            arr2[j] = (int) list2.get(j);
                        }
                        arr[i] = arr2;
                    }
                    data.add(arr);
                } else if (typeBuffer.getClass().getComponentType() == String.class) {
                    String[][] arr = new String[list.size()][];
                    for (int i = 0; i < arr.length; ++i) {
                        List<Object> list2 = (List<Object>) list.get(i);
                        arr[i] = (String[]) list2.toArray(typeBuffer);
                    }
                    data.add(arr);
                } else {
                    System.out.println(typeBuffer.getClass().getComponentType());
                }
            }
            return Status.WAITING;
        } else {
            List<Object> list2 = listBuffer.pop();
            listBuffer.peek().add(list2);
            return Status.WAITING_ARRAY;
        }
    }

    static ListNode toListNode(List<Integer> list) {
        ListNode head = null;
        ListNode ptr = null;
        for (int i : list) {
            ListNode node = new ListNode(i);
            if (ptr == null) {
                head = node;
            } else {
                ptr.next = node;
            }
            ptr = node;
        }
        return head;
    }

    static boolean isNum(char c) {
        return c >= '0' && c <= '9';
    }

    static boolean isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

}

class Data {
    List<Object> objects;

    public Data() {
        objects = new ArrayList<>();
    }

    public void add(Object o) {
        objects.add(o);
    }

    public boolean canAccept(Method method) {
        if (method.getParameterCount() != objects.size()) {
            return false;
        }
        Class<?>[] args = method.getParameterTypes();
        for (int i = 0; i < args.length; ++i) {
            if (!isSameType(objects.get(i).getClass(), args[i])) {
                return false;
            }
        }
        return true;
    }

    private boolean isSameType(Class<?> o, Class<?> c) {
        if (o == Integer.class && c == int.class) {
            return true;
        }
        if (o.getComponentType() != null && c.getComponentType() != null) {
            return isSameType(o.getComponentType(), c.getComponentType());
        }
        return o == c;
    }

    public Object invoke(Method method, Object instance) {
        Object[] objs = objects.toArray();
        try {
            return method.invoke(instance, objs);
        } catch (InvocationTargetException | IllegalAccessException e) {
            e.printStackTrace();
        }
        return null;
    }

    public String toString() {
        StringBuilder builder = new StringBuilder("[");
        for (int i = 0; i < objects.size(); i++) {
            builder.append(objects.get(i).toString());
            if (i != objects.size() - 1) {
                builder.append(", ");
            }
        }
        builder.append("]");
        return builder.toString();
    }

    public String toTypeString() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < objects.size(); i++) {
            builder.append(objects.get(i).getClass().getTypeName());
        }
        return builder.toString();
    }
}
