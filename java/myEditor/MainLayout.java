import java.awt.*;
import javax.swing.*;

public class MainLayout extends JFrame 
{
    private JTabbedPane tabbedPane;
    //private PanelGridLayout panelGridLayout;
    
    public MainLayout() {
        setTitle("MyEditor");  //设置标题
        setBounds(200, 100, 1000, 800);  //设置边界及窗口位置

        //核心布局
        tabbedPane = new JTabbedPane();
        //tabbedPane.add(panelGridLayout);

        
        setVisible(true);  //使窗口可见
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);  //点击关闭按钮销毁窗口
    }

}