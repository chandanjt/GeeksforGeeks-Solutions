

//User function Template for javascript

/**
 * @param {number[]} a1
 * @param {number[]} a2
 * @param {number} n
 * @param {number} m
 * @returns {string}
*/

class Solution{
    isSubset(a1, a2, n, m){
        //code here
        let subset = "Yes";
        for(let i = 0; i<m; i++) {
            if(a1.includes(a2[i]) == false){
                subset = "No";
                break;
            }else{
               let index = a1.indexOf(a2[i]);
                a1.splice(index,1);
            }
        }
        return subset;
    }
}

