public class HelloFriends {
    public static void main(String args[]) {
        int i;

        for (i = 0; i < args.length; i++) {
            System.out.println("#" + (i + 1) + ". Hello " + args[i]);
        }
    }
}

