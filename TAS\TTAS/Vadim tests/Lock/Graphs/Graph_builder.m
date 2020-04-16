% graph builder
function y = Graph_builder(A)
    x = A(:,1:1);
   
    y = A(:,2:5);
    
    
    %disp(y);
    
    plot(x, y, 'LineWidth', 2);
   
   
    %axis([1 200 0 0.02]);
    
    
    str_arr = string(4);
    str_arr(1) = ' - TAS';
    str_arr(2) = ' - TTAS';
    str_arr(3) = ' - exp TTAS';
    str_arr(4) = ' - pause TTAS';
    grid on;
    title('Lock')
    xlabel('threads')
    ylabel('time, sec')
    lgd = legend(str_arr, 'Location','northwest');
    lgd.FontSize = 8;
    
    print('Graphs.png','-dpng','-r300');  
end

