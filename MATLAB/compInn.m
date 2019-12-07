function inn = compInn(frame, threshold, ref_inn, ixx)
% Determines if there is speech or not. In case there is, updates the
% estimated value of Inn(wk)
% Inputs    :   frame       :   Array representing the current sample frame
%                               to compute
%               threshold  	:   Value representing the threshold which 
%                               determines speech or not
%               ref_inn     :   Array of size 3 representing the three last
%                               values of the estimate Inn used
%                              	as reference
%               ixx         :   Array reprensenting the periodogram of the
%                               current noisy signal sample
% Outputs   :   inn         :   Array reprensenting the periodogram of the 
%                               current noise sample

    % If the energy of the current sample is greater than the threshold, we
    % consider there is speech
    if(compEnergy(frame) >= threshold)
        % Therefore, the estimate value of inn is not updated
        inn = ref_inn(1, 1:end);
    
    else
        % If periodogram of corrupted speech is less than noise's, we
        % update it
        if(mean(ixx) < mean(ref_inn(1, 1:end)))
            inn = ixx;        
            
        else
            % Compute the mean values of the three last inn and take the smallest
            [~, ind_min_val] = min(mean(ref_inn, 2));       
            inn = ref_inn(ind_min_val, 1 : end);
        end 
    end
    
    inn = halfWaveRect(inn);
end

