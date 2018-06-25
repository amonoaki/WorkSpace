import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Layout extends JFrame 
{
    private JTabbedPane jTabbedPane = new JTabbedPane();
    private JMenuBar jMenuBar = new JMenuBar();
    private JMenu file = new JMenu("File");
    private JMenuItem openFile, newFile, saveFile;

    public Layout() {
        setTitle("MyEditor");  //设置标题
        setBounds(200, 100, 1000, 800);  //设置边界及窗口位置
        setLayout(new GridLayout(1, 1));
        init();  //完成初始化窗口工作
        setVisible(true);  //使窗口可见
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);  //点击关闭按钮销毁窗口
    }

    private void init() {

        /*菜单栏*/
        //设置子菜单
        openFile = new JMenuItem("Open File");
        newFile = new JMenuItem("New File");
        saveFile = new JMenuItem("Save File");
        //设置菜单项
        file.add(openFile);
        file.add(newFile);
        file.add(saveFile);
        //添加菜单项
        jMenuBar.add(file);
        //添加菜单
        setJMenuBar(jMenuBar);

        /*主面板*/
        add(jTabbedPane);
        JTextArea welcomePage = new JTextArea("This is the welcome page.");
        jTabbedPane.add("Welcome Page", welcomePage);
    }
}